package org.ioopm.calculator.ast;

public class NamedConstant extends Constant {
    String name;
    
    public NamedConstant(String name, double value) {
        this.name = name;
        super(value);
    }
    
    public boolean isNamedConstant() {
        return true;
    }

    public String toString() {
    return this.name;
}


}




