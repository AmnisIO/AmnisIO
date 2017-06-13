import { FunctionLikeDeclaration, Identifier } from 'typescript';
import { Context } from '../contexts';
import { EmitResult } from './';

export const emitFunctionLikeDeclaration = (node: FunctionLikeDeclaration, context: Context): EmitResult => {
  return {
    context,
    emitted_string: 'function declaration of ' + (node.name as Identifier).text
  };
}
