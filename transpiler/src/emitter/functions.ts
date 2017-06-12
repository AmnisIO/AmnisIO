import { FunctionLikeDeclaration, Identifier } from 'typescript';

export const emitFunctionLikeDeclaration = (node: FunctionLikeDeclaration): string => {
  return 'function declaration of ' + (node.name as Identifier).text;
}
