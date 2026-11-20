package org.ioopm.calculator.ast;

public class Assignment extends Binary {
    
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "=";
    }

    public int getPriority() {
        return 10;
    }

    public String toString() {
        return getLhs().toString() + " " + getName() + " " + getRhs().toString();
    }

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression lhs = getLhs().eval(vars);
    SymbolicExpression rhs = getRhs();
    if (rhs.isNamedConstant()) {
        throw new IllegalAssignmentException();
    }
    if (lhs.isConstant() && rhs.isVariable()) {
        vars.put((Variable) rhs, lhs);
        return new Constant(lhs.getValue());
    } else {
        return new Assignment(lhs, rhs);
    }
    }
}
