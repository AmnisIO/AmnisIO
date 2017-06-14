import { Identifier, TypeReferenceNode } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit } from './';

export const emitIdentifier = ({ text }: Identifier, context: Context): EmitResult => ({
  context,
  emitted_string: sanitize(context[text] == undefined ? text : context[text])
});

export const emitType = ({ typeName }: TypeReferenceNode, context: Context): EmitResult => emit(typeName, context);

const sanitize = (value: string): string => value.replace(/\$/g, '');
