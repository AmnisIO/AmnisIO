import { FunctionLikeDeclaration, Identifier, TypeReferenceNode, VariableDeclaration } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit, emitString } from './';

const emitFunctionDeclaration = (node: FunctionLikeDeclaration, context: Context): string => {
  const return_type = emitString(node.type, context);
  const function_name = emitString(node.name, context);
  const parameters =
    node.parameters
      .map(p => ({ name: emitString(p.name, context), type: emitString(p.type, context)}))
      .map(({ name, type }) => `${type} ${name}`)
      .join(', ');
  const body = emitString(node.body, context);
  const declaration = `${return_type} ${function_name}(${parameters}) ${body}`;
  return declaration;
};

export const emitFunctionLikeDeclaration = (node: FunctionLikeDeclaration, context: Context): EmitResult => {
  return {
    context,
    emitted_string: emitFunctionDeclaration(node, context)
  };
}

export const emitVariableDeclaration = ({ type, name, initializer }: VariableDeclaration, context: Context): EmitResult => {
  return {
    context,
    emitted_string: `${emitString(type, context)} ${emitString(name, context)} = ${emitString(initializer, context)}`
  }
};
