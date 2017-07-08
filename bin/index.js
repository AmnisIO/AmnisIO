#!/usr/bin/env node

var yargs = require('yargs');
var findUp = require('find-up');
var fs = require('fs');
var path = require('path');
var shell = require('shelljs');
var fetch = require('node-fetch');


var cwd = yargs.argv.cwd || process.cwd();
var amnisio_dir = path.join(cwd, 'node_modules/amnisio');
var amnisio_dist_dir = path.join(amnisio_dir, 'dist');
var amnisio_config_dir = amnisio_dist_dir;
var amnisio_typewriter_path = path.join(cwd, 'node_modules/.bin/typewriter');
var board_configs = require(amnisio_config_dir).configs;

var configPath = findUp.sync(['.amnisio.config.json']);
var config = configPath ? JSON.parse(fs.readFileSync(configPath)) : {};

var argv =
  yargs
    .config(config)
    .usage('Usage: $0 <command> [options]')
    // Initialize
    .command('init', 'Initialize to a particular board configuration', () => {}, argv => {
      if(!shell.which('platformio') || !shell.which('pio')) {
        shell.echo('platformio is required but not found.\n');
        shell.echo('please install platformio-core, refer http://docs.platformio.org/en/latest/installation.html\n');
        shell.echo('also please make sure that platformio executable is added to PATH\n');
        shell.echo('on bash, use export PATH=~/.platformio/penv/bin:$PATH')
        shell.exit(1);
      }
      var board_configuration = board_configs[argv.b];
      var board = board_configuration.board;
      var libraries = board_configuration.libraries;
      var dependencies = board_configuration.dependencies;
      shell.echo('Selected platform ' + board);
      shell.echo('Installing npm dependencies');
      shell.exec('npm install --save-dev ' + dependencies.join(' '));
      shell.echo('Clearing .amnisio');
      shell.rm('-rf', '.amnisio');
      shell.mkdir('.amnisio');
      shell.echo('Creating platformio project with board configuration ' + board);
      shell.exec('platformio init -d .amnisio -b ' + board);
      shell.echo('Adding library files to platformio project');
      var contentUrls = libraries.reduce((list, lib) => {
        // ONLY GITHUB REPOSITORIES
        var splitPath = lib.repository.split('/').filter(x => !!x);
        var repository = splitPath.pop();
        var user = splitPath.pop();
        var url = 'https://api.github.com/repos/' + user + '/' + repository + '/contents/';
        var paths = lib.paths.map(p => url + p);
        return list.concat(paths);
      }, []);
      Promise
        .all(contentUrls.map(url => fetch(url).then(response => response.json())))
        .then(contents_list => contents_list.reduce((urls, list) => urls.concat(list), []))
        .then(files => files.filter(file => file.type === 'file'))
        .then(files => {
          shell.mkdir('.amnisio/lib/Gyrus');
          var outputFilePrefix = path.join(cwd, '.amnisio', 'lib', 'Gyrus');
          return Promise.all(files.map(file => {
            var outFile = path.join(outputFilePrefix, file.name);
            return fetch(file.download_url)
              .then(response => response.text())
              .then(content => fs.writeFileSync(outFile, content));
          })).then(() => {
            shell.echo('All done, thanks!\n');
            shell.exit(0);
          });
        });
    })
    .alias('b', 'board')
    .nargs('b', 1)
    .demandOption(['b'])
    .help('h')
    .alias('h', 'help')
    .example('$0 init -b uno', 'Initialize to a the Arduino Uno board configuration')
    // Build
    .command('build', 'Build the AmnisIO project', () => {}, argv => {
      var source = path.join(cwd, argv.source || 'app.ts');
      var output = path.join(cwd, '.amnisio', 'src', argv.output || 'app.c');
      shell.exec(amnisio_typewriter_path + ' --file ' + source + ' --outfile ' + output);
      shell.exec('platformio run -d .amnisio');
    })
    .example('$0 build', 'Build the AmnisIO project')
    // Clean
    .command('clean', 'Clean the AmnisIO project', () => {}, argv => {
      shell.exec('platformio run -d .amnisio -t clean');
    })
    .example('$0 clean', 'Clean the AmnisIO project')
    // Deploy
    .command('deploy', 'Deploy the AmnisIO project to the selected platform', () => {}, argv => {
      var source = path.join(cwd, argv.source || 'app.ts');
      var output = path.join(cwd, '.amnisio', 'src', argv.output || 'app.c');
      shell.exec(amnisio_typewriter_path + ' --file ' + source + ' --outfile ' + output);
      shell.exec('platformio run -d .amnisio -t upload');
    })
    .example('$0 deploy', 'Deploy the AmnisIO project to the selected platform')
    .demand(1)
    .argv;
