import { getAST } from './ast';
import { emit } from './emitter';

declare function require(name: string);
declare var process: any;

(function () {
  if (typeof process !== 'undefined' && process.nextTick && !process.browser && typeof require !== "undefined") {
    var fs = require('fs');
    if (process.argv.length < 2)
      process.exit();
    var fileNames = process.argv.slice(2);
    const sourceFile = getAST(fileNames);
    const result = emit(sourceFile);
    console.log(result);
    process.exit();
  }
})();
