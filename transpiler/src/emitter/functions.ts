import { FunctionLikeDeclaration, Identifier, TypeReferenceNode } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit } from './';

const emitFunctionDeclaration = (node: FunctionLikeDeclaration, context: Context): string => {
  const return_type = emit(node.type, context).emitted_string;
  const function_name = emit(node.name, context).emitted_string;
  const parameters =
    node.parameters
      .map(p => ({ name: emit(p.name, context).emitted_string, type: emit(p.type, context).emitted_string}))
      .map(({ name, type }) => `${type} ${name}`)
      .join(', ');
  const body = emit(node.body, context).emitted_string;
  const declaration = `${return_type} ${function_name}(${parameters}) ${body}`;
  return declaration;
};

export const emitFunctionLikeDeclaration = (node: FunctionLikeDeclaration, context: Context): EmitResult => {
  return {
    context,
    emitted_string: emitFunctionDeclaration(node, context)
  };
}
