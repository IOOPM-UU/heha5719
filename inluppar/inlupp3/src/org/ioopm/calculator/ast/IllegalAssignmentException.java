package org.ioopm.calculator.ast;

public class IllegalAssignmentException extends RuntimeException {
    public IllegalAssignmentException() {
       System.out.println("Error: cannot redefine named constant") ;
    }
}