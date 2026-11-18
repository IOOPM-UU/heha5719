package org.ioopm.calculator.ast;

public class Exp extends Unary {
    
    public Exp(SymbolicExpression tree) {
        super(tree);
    }

    public String getName() {
        return "exp";
    }

    public int getPriority() {
        return 100;
    }

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression arg = this.getTree().eval(vars);
    if (arg.isConstant()) {
        return new Constant(Math.exp(arg.getValue()));
    } else {
        return new Exp(arg);
    }
    }
}