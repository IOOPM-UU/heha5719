package org.ioopm.calculator.ast;

public class Subtraction extends Binary {
    
    public Subtraction(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "-";
    }

    public int getPriority() {
        return 50;
    }

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression lhs = getLhs().eval(vars);
    SymbolicExpression rhs = getRhs().eval(vars);
    if(lhs.isConstant() && rhs.isConstant()) {
        return new Constant(lhs.getValue() - rhs.getValue());
    } else {
        return new Subtraction(lhs, rhs);
    }
    }
}
