package org.ioopm.calculator.parser;

import java.util.HashMap;

public class Constants {
    public static final HashMap<String, Double> NamedConstant = new HashMap<>();

    static { 
        Constants.NamedConstant.put("pi", Math.PI);
        Constants.NamedConstant.put("Answer", 42.0);
        Constants.NamedConstant.put("e",  Math.E);
        Constants.NamedConstant.put("L", 6.022140857 * Math.pow(10, 23));
    }
}