package org.ioopm.calculator.ast;

public class Log extends Unary {
    
    public Log(SymbolicExpression tree) {
        super(tree);
    }

    public String getName() {
        return "log";
    }

    public int getPriority() {
        return 50;
    }

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression arg = this.getTree().eval(vars);
    if (arg.isConstant()) {
        return new Constant(Math.log(arg.getValue()));
    } else {
        return new Log(arg);
    }
}
}
