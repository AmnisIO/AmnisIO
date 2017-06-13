import { ImportDeclaration, NamedImports, StringLiteral } from 'typescript';
import { Context, getContext } from '../contexts';
import { EmitResult } from './';

export const emitImportDeclaration = (node: ImportDeclaration, context: Context): EmitResult => {
  const module_specifier = (node.moduleSpecifier as StringLiteral).text.split('/').pop();
  const module_header = module_specifier.replace(/\-/ig, '_');
  const module_context = getContext(module_specifier);
  return {
    context: {
      ...context,
      ...module_context
    },
    emitted_string: `#include "riot_${module_header}.h"`
  };
}
