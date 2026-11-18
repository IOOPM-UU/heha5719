package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    private SymbolicExpression tree = null;

    public Unary(SymbolicExpression tree) {
        this.tree = tree;
    }

    public String toString() {
        String tree = this.tree.toString();
        if (this.tree.getPriority() < this.getPriority()) {
            tree = "(" + tree + ")";
        }
        return this.getName() + " " + tree;
        }


    public int getPriority() {
        return 0;
    }
    
    public boolean equals(Object other) {
    if (other instanceof Unary) {
        return this.equals((Unary) other);
    } else {
        return false;
    }
    }
    
    public SymbolicExpression getTree() {
        return this.tree;
    }

    public boolean equals(Unary other) {
    /// access a private field of other!
    return this.getName().equals(other.getName()) && this.tree.equals(other.tree);
    }
}
