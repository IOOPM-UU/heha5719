package org.ioopm.calculator.ast;

public class Constant extends Atom {
    private double value;

public Constant(double value) {
    this.value = value;
}

public boolean isConstant() {
    return true;
}
 
public double getValue() {
    return value;
}

  public int getPriority() {
        return 200;
    }

public String toString() {
    return String.valueOf(this.value);
}

public boolean equals(Object other) {
    if (other instanceof Constant) {
        return this.equals((Constant) other);
    } else {
        return false;
    }
}

public boolean equals(Constant other) {
    /// access a private field of other!
    return this.value == other.value;
}

public SymbolicExpression eval(Environment vars) {
    return new Constant(this.value);
}
}