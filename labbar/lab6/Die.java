import java.util.Scanner;

public class Die {
    private int numberOfSides;
    private int value;
    public boolean equals(Die otherdie) {
        if (value == otherdie.value && numberOfSides == otherdie.numberOfSides) {
            return true;
        }
        else {
            return false;
        }
    }

public Die() {
    this.numberOfSides = 6;
    this.roll();
}

public Die(int numberOfSides) {
    if (numberOfSides < 1) {
        throw new IllegalArgumentException(numberOfSides + " is an illegal number of sides for a die!");
    }
    this.numberOfSides = numberOfSides;
    this.roll();
}

public int roll() {
    this.value = (int) (Math.random() * numberOfSides) + 1;
    return this.get();
}
public int get() {
    return value;
}

public String toString() {
    return "Die(" + value + ")";
}

public static void main(String [] args) {
    // 1.2.5 
    /* Die d1 = new Die();
    Die d2 = new Die();

    System.out.println("Are the dices equal? " + d1.equals(d2));
    */

    // 1.2.4
     /* 
    Die d = new Die();
    System.out.println(d);
    */
    // 1.2.1 - 1.2.3
      
    Scanner sc = new Scanner(System.in);
    System.out.print("Number of sides: ");
    int sides = sc.nextInt();
    Die d = new Die(sides);
    System.out.println("Alea iacta est: " + d.roll());
    
}
}