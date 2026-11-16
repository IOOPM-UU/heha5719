package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    private SymbolicExpression tree = null;

    public Unary(SymbolicExpression tree) {
        this.tree = tree;
    }
}
