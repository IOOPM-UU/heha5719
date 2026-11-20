package org.ioopm.calculator.ast;


public class Test {
    private static int passed = 0;
    private static int failed = 0;
 
    // =====================================================================
    // Test helpers
    // =====================================================================
 
    public static void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
            passed++;
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
            failed++;
        }
        assert expected.equals("" + e) : "expected '" + expected + "' but got '" + e + "'";
    }
 
    /// Checks that a.equals(b) gives the expected answer, and if b is an
    /// expression, also that b.equals(a) gives the same answer (symmetry).
    public static void testEquals(boolean expected, SymbolicExpression a, Object b) {
        boolean forward = a.equals(b);
        boolean backward = (b instanceof SymbolicExpression) ? b.equals(a) : expected;
        boolean ok = forward == expected && backward == expected;
 
        String description = "'" + a + "'.equals('" + b + "')";
        if (ok) {
            System.out.println("Passed: " + description + " == " + expected);
            passed++;
        } else if (forward != backward) {
            System.out.println("Error: equals is not symmetric for " + description);
            failed++;
        } else {
            System.out.println("Error: " + description + " should be " + expected);
            failed++;
        }
        assert ok : description + " failed";
    }
 
    /// Checks that two equal variables have the same hash code. Needed for
    /// variables to work as keys in the Environment (a HashMap) in step B7.
    public static void testHashCode(SymbolicExpression a, SymbolicExpression b) {
        boolean ok = a.hashCode() == b.hashCode();
        if (ok) {
            System.out.println("Passed: hashCode of '" + a + "' and '" + b + "' are equal");
            passed++;
        } else {
            System.out.println("Error: '" + a + "' and '" + b + "' are equal but have different hash codes");
            failed++;
        }
        assert ok : "hashCode differs for '" + a + "' and '" + b + "'";
    }
 
    /// Until eval() is implemented, let eval() in SymbolicExpression return
    /// null. Then every evaluation test fails, as the assignment says.
    ///
    /// In step B7, eval() gets an Environment argument. Then you only need to
    /// change the eval call below to e.eval(new Environment()) -- a fresh
    /// environment per test, so that no side effects carry over between tests.
    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e) {
        SymbolicExpression r = e.eval(new Environment());
        boolean ok = r != null && r.equals(expected);
        if (ok) {
            System.out.println("Passed: " + e + " ==> " + r);
            passed++;
        } else {
            System.out.println("Error: " + e + " should evaluate to '" + expected + "' but got '" + r + "'");
            failed++;
        }
        assert ok : e + " should evaluate to '" + expected + "' but got '" + r + "'";
    }
 
    // =====================================================================
    // Shorthands to make the tests easier to read
    // =====================================================================
 
    private static Constant num(double value) { return new Constant(value); }
    private static Variable var(String name)  { return new Variable(name); }
 
    /// sin x + 5 * a - 3 * (u + 1) = z = t
    private static SymbolicExpression bigExpression() {
        return new Assignment(
            new Assignment(
                new Subtraction(
                    new Addition(new Sin(var("x")), new Multiplication(num(5), var("a"))),
                    new Multiplication(num(3), new Addition(var("u"), num(1)))),
                var("z")),
            var("t"));
    }
 
    // =====================================================================
    // Printing tests (step B4/B5)
    // =====================================================================
 
    public static void printingTests() {
        System.out.println("===== Printing =====");
        Variable a = var("a"), b = var("b"), c = var("c"), d = var("d");
        Variable x = var("x"), y = var("y");
 
        // The example from the assignment
        testPrinting("(5.0 + x) * 2.0", new Multiplication(new Addition(num(5), x), num(2)));
 
        // Atoms
        testPrinting("42.0", num(42));
        testPrinting("3.14", num(3.14));
        testPrinting("0.0", num(0));
        testPrinting("x", x);
 
        // Simple binary expressions
        testPrinting("5.0 + x", new Addition(num(5), x));
        testPrinting("x - 3.0", new Subtraction(x, num(3)));
        testPrinting("2.0 * x", new Multiplication(num(2), x));
        testPrinting("x / 2.0", new Division(x, num(2)));
 
        // Priority: no parentheses needed
        testPrinting("5.0 + x * 2.0", new Addition(num(5), new Multiplication(x, num(2))));
        testPrinting("a * b + c * d", new Addition(new Multiplication(a, b), new Multiplication(c, d)));
        testPrinting("a * b * c / d", new Multiplication(new Multiplication(a, b), new Division(c, d)));
 
        // Priority: parentheses needed
        testPrinting("(a + b) * (c - d)", new Multiplication(new Addition(a, b), new Subtraction(c, d)));
        testPrinting("(a + b) * c * d", new Multiplication(new Addition(a, b), new Multiplication(c, d)));
        testPrinting("a * (b + c)", new Multiplication(a, new Addition(b, c)));
        testPrinting("(a - b) / c", new Division(new Subtraction(a, b), c));
 
        // Same priority, left-nested: no parentheses
        testPrinting("a + b + c", new Addition(new Addition(a, b), c));
        testPrinting("a - b - c", new Subtraction(new Subtraction(a, b), c));
        testPrinting("a / b / c", new Division(new Division(a, b), c));
 
        // Same priority, right-nested: the tricky cases
        testPrinting("a + b - c", new Addition(a, new Subtraction(b, c)));
 
        // Unary expressions
        testPrinting("sin x", new Sin(x));
        testPrinting("cos 5.0", new Cos(num(5)));
        testPrinting("exp x", new Exp(x));
        testPrinting("log x", new Log(x));
        testPrinting("- x", new Negation(x));
        testPrinting("log log x", new Log(new Log(x)));
        testPrinting("- - x", new Negation(new Negation(x)));
        testPrinting("sin cos x", new Sin(new Cos(x)));
        testPrinting("exp (x + 1.0)", new Exp(new Addition(x, num(1))));
        testPrinting("- (x + y)", new Negation(new Addition(x, y)));
        testPrinting("sin (2.0 * x)", new Sin(new Multiplication(num(2), x)));
        testPrinting("sin x * 2.0", new Multiplication(new Sin(x), num(2)));
        testPrinting("2.0 * sin (x + y)", new Multiplication(num(2), new Sin(new Addition(x, y))));
        testPrinting("- x + y", new Addition(new Negation(x), y));
 
        // Assignment
        testPrinting("5.0 = x", new Assignment(num(5), x));
        testPrinting("1.0 + 2.0 = x", new Assignment(new Addition(num(1), num(2)), x));
        testPrinting("2.0 = x = y", new Assignment(new Assignment(num(2), x), y));
        testPrinting("(1.0 = x) + 2.0", new Addition(new Assignment(num(1), x), num(2)));
 
        // A big expression from the assignment text
        testPrinting("sin x + 5.0 * a - 3.0 * (u + 1.0) = z = t", bigExpression());
    }
 
    // =====================================================================
    // Equality tests (step B6)
    // =====================================================================
 
    public static void equalsTests() {
        System.out.println();
        System.out.println("===== Equality =====");
        Variable a = var("a"), b = var("b");
        Variable x = var("x"), y = var("y");
 
        // Reflexivity: an object is always equal to itself
        SymbolicExpression same = new Addition(num(1), x);
        testEquals(true, same, same);
 
        // Constants
        testEquals(true,  num(5), num(5));
        testEquals(false, num(5), num(6));
        testEquals(true,  num(1), num(1.0));
        // 0.1 + 0.2 is not exactly 0.3 in floating point arithmetic
        testEquals(false, num(0.1 + 0.2), num(0.3));
 
        // Variables: different objects with the same name are equal
        testEquals(true,  var("x"), var("x"));
        testEquals(false, var("x"), var("y"));
        testEquals(false, var("x"), var("X"));                              // case sensitive
        testEquals(false, num(5), var("x"));
 
        // Unary: same operator and same subtree
        testEquals(true,  new Sin(x), new Sin(var("x")));
        testEquals(false, new Sin(x), new Sin(y));                          // subtree matters
        testEquals(false, new Sin(x), new Cos(x));                          // operator matters
        testEquals(false, new Exp(x), new Log(x));
        testEquals(false, new Log(x), new Negation(x));
        testEquals(false, new Sin(new Cos(x)), new Cos(new Sin(x)));        // nesting order matters
 
        // Binary: same operator and same subtrees
        testEquals(true,  new Addition(num(5), x), new Addition(num(5), var("x")));
        testEquals(false, new Addition(a, b), new Subtraction(a, b));       // operator matters
        testEquals(false, new Multiplication(a, b), new Division(a, b));
        testEquals(false, new Assignment(a, b), new Addition(a, b));        // Assignment is a Binary too
        testEquals(false, new Addition(a, b), new Addition(b, a));          // order matters
        testEquals(false, new Addition(a, b), new Addition(a, x));          // only rhs differs
        testEquals(false, new Addition(a, b), new Addition(x, b));          // only lhs differs
 
        // Different kinds of nodes
        testEquals(false, new Negation(x), x);
        testEquals(false, new Negation(x), new Subtraction(num(0), x));    // same meaning, different tree
 
        // Deep trees: equal, and differing only in one leaf far down
        testEquals(true,  bigExpression(), bigExpression());
        testEquals(false,
                new Sin(new Addition(new Multiplication(num(2), x), num(1))),
                new Sin(new Addition(new Multiplication(num(3), x), num(1))));
 
        // Comparing with things that are not expressions
        testEquals(false, num(5), null);
        testEquals(false, var("x"), "x");                                   // a String, not a Variable
        testEquals(false, num(5), Double.valueOf(5));                       // a Double, not a Constant
 
        // Hash codes for variables (needed in step B7)
        testHashCode(var("x"), var("x"));
        testHashCode(var("answer"), var("answer"));
    }
 
    // =====================================================================
    // Evaluation tests (step B6/B7), isomorphic to the printing tests
    // =====================================================================
 
    public static void evaluationTests() {
        System.out.println();
        System.out.println("===== Evaluation =====");
        Variable a = var("a"), b = var("b"), c = var("c");
        Variable x = var("x"), y = var("y");
 
        // The example from the assignment: cannot be reduced
        testEvaluating(new Multiplication(new Addition(num(5), x), num(2)),
                       new Multiplication(new Addition(num(5), x), num(2)));
        // ...but with constants only it can
        testEvaluating(num(16), new Multiplication(new Addition(num(5), num(3)), num(2)));
 
        // Atoms evaluate to themselves
        testEvaluating(num(42), num(42));
        testEvaluating(x, x);
 
        // Simple binary expressions with constants
        testEvaluating(num(42),   new Addition(num(5), num(37)));
        testEvaluating(num(7),    new Subtraction(num(10), num(3)));
        testEvaluating(num(42),   new Multiplication(num(6), num(7)));
        testEvaluating(num(0.25), new Division(num(1), num(4)));
 
        // Simple binary expressions with a variable: no reduction
        testEvaluating(new Addition(num(5), x), new Addition(num(5), x));
        testEvaluating(new Division(x, num(2)), new Division(x, num(2)));
 
        // Partial reduction: constant subtrees are folded
        testEvaluating(new Addition(num(6), x),
                       new Addition(new Multiplication(num(2), num(3)), x));
        testEvaluating(new Multiplication(x, num(5)),
                       new Multiplication(x, new Division(num(10), num(2))));
        testEvaluating(new Multiplication(new Addition(a, b), new Subtraction(c, num(3))),
                       new Multiplication(new Addition(a, b), new Subtraction(c, new Subtraction(num(4), num(1)))));
 
        // Priority and associativity with numbers
        testEvaluating(num(13), new Addition(num(5), new Multiplication(num(4), num(2))));
        testEvaluating(num(18), new Multiplication(new Addition(num(5), num(4)), num(2)));
        testEvaluating(num(7),  new Subtraction(num(10), new Subtraction(num(4), num(1))));
        testEvaluating(num(5),  new Subtraction(new Subtraction(num(10), num(4)), num(1)));
        testEvaluating(num(4),  new Division(num(16), new Division(num(8), num(2))));
        testEvaluating(num(1),  new Division(new Division(num(16), num(8)), num(2)));
 
        // Only constant subtrees are folded -- no algebraic simplification
        testEvaluating(new Addition(num(3), x), new Addition(new Addition(num(1), num(2)), x));
        testEvaluating(new Addition(new Addition(x, num(1)), num(2)),
                       new Addition(new Addition(x, num(1)), num(2)));
 
        // Unary expressions with constants
        testEvaluating(num(Math.sin(0)), new Sin(num(0)));
        testEvaluating(num(Math.cos(0)), new Cos(num(0)));
        testEvaluating(num(Math.exp(1)), new Exp(num(1)));
        testEvaluating(num(Math.log(1)), new Log(num(1)));
        testEvaluating(num(-5), new Negation(num(5)));
        testEvaluating(num(5),  new Negation(new Negation(num(5))));
        testEvaluating(num(Math.exp(5)), new Exp(new Addition(num(2), num(3))));
 
        // Unary expressions with variables
        testEvaluating(new Negation(x), new Negation(x));
        testEvaluating(new Sin(x), new Sin(x));
        testEvaluating(new Sin(new Addition(x, num(2))),
                       new Sin(new Addition(x, new Addition(num(1), num(1)))));
        testEvaluating(new Addition(new Negation(x), num(9)),
                       new Addition(new Negation(x), new Multiplication(num(3), num(3))));
 
        // Assignment evaluates to the value of its left-hand side
        testEvaluating(num(5), new Assignment(num(5), x));
        testEvaluating(num(3), new Assignment(new Addition(num(1), num(2)), x));
        testEvaluating(num(2), new Assignment(new Assignment(num(2), x), y));
        testEvaluating(num(3), new Addition(new Assignment(num(1), x), num(2)));
        
        // Some errors are left to Java: 1 / 0 is Infinity
        testEvaluating(num(Double.POSITIVE_INFINITY), new Division(num(1), num(0)));

        // Named constants behave like their value
    testEvaluating(new Constant(84), new Addition(new NamedConstant("Answer", 42), new NamedConstant("Answer", 42)));

    testPrinting("pi", new NamedConstant("pi", Math.PI));

    // Redefining a named constant throws
    try { 
        new Assignment(new Constant(43), new NamedConstant("Answer", 42)).eval(new Environment());
        System.out.println("Error: expected IllegalAssignmentException");
        failed++;
    }  catch (IllegalAssignmentException e) {
        System.out.println("Passed: " + e.getMessage());
        passed++;
    }
    }
 
    // =====================================================================
 
    public static void main(String[] args) {
        printingTests();
        equalsTests();
        evaluationTests();
 
        System.out.println();
        System.out.println(passed + " passed, " + failed + " failed");
    }
}
