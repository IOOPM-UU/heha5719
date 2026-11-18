package org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {
    private SymbolicExpression lhs = null;
    private SymbolicExpression rhs = null;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        this.lhs = lhs;
        this.rhs = rhs;
    }

    protected boolean isAssociative() {
    return true; 
    }

    public String toString() {
        if (lhs.getPriority() < this.getPriority()) {
            if (rhs.getPriority() < this.getPriority()) {
                return "(" + this.lhs.toString() + ") " + this.getName() + " (" + this.rhs.toString() + ")";
            }
            return "(" + this.lhs.toString() + ") " + this.getName() + " " + this.rhs.toString();
        }
        else if (rhs.getPriority() < this.getPriority()) {
            return this.lhs.toString() + " " + this.getName() + " (" + this.rhs.toString() + ")";
        }
        else {
            return this.lhs.toString() + " " + this.getName() + " " + this.rhs.toString();
        }
    }



    public int getPriority() {
        return 100;
    }

    public SymbolicExpression getLhs() {
        return this.lhs;
    }

    public SymbolicExpression getRhs() {
        return this.rhs;
    }
    
    
    public boolean equals(Object other) {
        if (other instanceof Binary) {
            return this.equals((Binary) other);
        } else {
            return false;
        }
    }

    public boolean equals(Binary other) {
        return this.getName().equals(other.getName()) && 
        this.lhs.equals(other.lhs) && 
        this.rhs.equals(other.rhs);
        }
}

