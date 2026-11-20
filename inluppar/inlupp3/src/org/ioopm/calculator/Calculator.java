package org.ioopm.calculator;

import java.util.HashMap;

import org.ioopm.calculator.ast.*;

import org.ioopm.calculator.parser.*;

public class Calculator {
        public static void main(String[] args) {
        System.out.println("Calculator started!");

        final Environment variables = new Environment();
        final CalculatorParser parser = new CalculatorParser();

        while (true) {

        String input = System.console().readLine();

        SymbolicExpression NewObject = parser.parse(input, variables);

        if (NewObject.isCommand()) {
            if (NewObject == Quit){
                System.out.println("Thank you for calculating!");
                Quit.instance();
                break;
            }   
            else if (NewObject == Vars){
                Vars.instance();  
            }
            else if (NewObject == Clear) {
                Clear.instance();
            }
        }
        // continue program
            


        
        /*
        * Read a string from the console
        Feed this string into the parser and get back a SymbolicExpression object
        Branch on this object
        If it is a command, we need to do whatever it wants (quit the program, clear the variable list, or print the variable list)
        Otherwise, we want to:
        Evaluate the SymbolicExpression object using the current variable list
        Assign the result to the variable ans
        Show the result to the user
        Go back to 1. and start over 
        */
    }
    }
   
}
