import * as ts from 'typescript';
import { Node, CompilerOptions, CompilerHost, SourceFile, SyntaxKind, FunctionLikeDeclaration, Identifier } from 'typescript';
import * as path from 'path';

declare function require(name: string);
declare var process: any;

function createCompilerHost(options: ts.CompilerOptions, moduleSearchLocations: string[]): ts.CompilerHost {
    return {
        getSourceFile,
        getDefaultLibFileName: () => "lib.d.ts",
        writeFile: (fileName, content) => ts.sys.writeFile(fileName, content),
        getCurrentDirectory: () => ts.sys.getCurrentDirectory(),
        getCanonicalFileName: fileName => ts.sys.useCaseSensitiveFileNames ? fileName : fileName.toLowerCase(),
        getNewLine: () => ts.sys.newLine,
        useCaseSensitiveFileNames: () => ts.sys.useCaseSensitiveFileNames,
        fileExists,
        readFile,
        resolveModuleNames,
        getDirectories: () => []
    }
    
    function fileExists(fileName: string): boolean {
        return ts.sys.fileExists(fileName);
    }
    
    function readFile(fileName: string): string {
        return ts.sys.readFile(fileName);
    }
    
    function getSourceFile(fileName: string, languageVersion: ts.ScriptTarget, onError?: (message: string) => void) {
        const sourceText = ts.sys.readFile(fileName);
        return sourceText !== undefined ? ts.createSourceFile(fileName, sourceText, languageVersion) : undefined;
    }

    function resolveModuleNames(moduleNames: string[], containingFile: string): ts.ResolvedModule[] {
        return moduleNames.map(moduleName => {
            // try to use standard resolution
            let result = ts.resolveModuleName(moduleName, containingFile, options, {fileExists, readFile});
            if (result.resolvedModule) {
                return result.resolvedModule;
            }

            // check fallback locations, for simplicity assume that module at location should be represented by '.d.ts' file
            for (const location of moduleSearchLocations) {
                const modulePath = path.join(location, moduleName + ".d.ts");
                if (fileExists(modulePath)) {
                    return { resolvedFileName: modulePath }
                }
            } 
            return undefined;
        });
    }
}

function compile(sourceFiles: string[], moduleSearchLocations: string[]): void {
    const options: ts.CompilerOptions = { module: ts.ModuleKind.AMD, target: ts.ScriptTarget.ES5, noLib: true, allowJs: true };
    const host = createCompilerHost(options, moduleSearchLocations);
    const program = ts.createProgram(sourceFiles, options, host);
    console.log('Compiling...');
    const initialSourceFile = program.getSourceFiles()[0];
    const actualSourceFile = program.getSourceFiles()[1];
    emitSourceFile(actualSourceFile);
}

const emitSourceFile = (sourceFile: ts.SourceFile) => {
  sourceFile.forEachChild(emitNode);
}

const emitNode = (node: Node) => {
  switch(node.kind) {
    case SyntaxKind.ImportDeclaration:
      console.log('imports');
      break;
    case SyntaxKind.FunctionDeclaration:
      console.log('function declaration', ((node as FunctionLikeDeclaration).name as Identifier).text);
      break;
    case SyntaxKind.ExpressionStatement:
      console.log('expression statement');
      break;
    case SyntaxKind.EndOfFileToken:
      console.log('file ends');
      break;
    default:
      console.log('unknown syntax kind', SyntaxKind[node.kind]);
  }
};

(function () {

    if (typeof process !== 'undefined' && process.nextTick && !process.browser && typeof require !== "undefined") {
        var fs = require('fs');
        if (process.argv.length < 2)
            process.exit();
        var fileNames = process.argv.slice(2);
        compile(fileNames, []);
        process.exit()
    }
})();
