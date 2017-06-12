import { ImportDeclaration, NamedImports } from 'typescript';

export const emitImportDeclaration = (node: ImportDeclaration): string => {
  return 'import declaration of ' + (node.importClause.namedBindings as NamedImports).elements.map(el => el.name.text).join(', ');
}
