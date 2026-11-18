package org.ioopm.calculator.ast;

public class Cos extends Unary {
    
    public Cos(SymbolicExpression tree) {
        super(tree);
    }

    public int getPriority() {
        return 200;
    }

    public String getName() {
        return "cos";
    }

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression arg = this.getTree().eval(vars);
    if (arg.isConstant()) {
        return new Constant(Math.cos(arg.getValue()));
    } else {
        return new Cos(arg);
    }
    }
}
