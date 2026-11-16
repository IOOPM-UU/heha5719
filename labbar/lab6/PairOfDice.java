public class PairOfDice {
    private Die d1;
    private Die d2;

public PairOfDice () {
    this.d1 = new Die();
    this.d2 = new Die(); 
}

public PairOfDice(int numberOfSides) {
    this.d1 = new Die(numberOfSides);
    this.d2 = new Die(numberOfSides);
}

public int Dice1() {
    return d1.get();
}

public int Dice2() {
    return d2.get();
}

public String toString() {
    return "Dice 1 : " + Dice1() + " Dice 2 : " + Dice2() + " Total : " + (Dice1() + Dice2());
}

public int roll() {
    int value1 = d1.roll();
    int value2 = d2.roll();
    return value1 + value2;
}

public static void main(String[] args) {
    PairOfDice pair = new PairOfDice();
    System.out.println(pair);
    System.out.println("Roll result : " + pair.roll());
    System.out.println(pair);
}
}