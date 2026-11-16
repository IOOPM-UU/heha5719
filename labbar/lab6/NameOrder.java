import java.util.Scanner;

public class NameOrder {
    
public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Name 1 : ");
    String name1 = sc.nextLine();
    System.out.print("Name 2 : ");
    String name2 = sc.nextLine();
    if (name1.compareToIgnoreCase(name2) < 0) {
        System.out.println(name1);
        System.out.println(name2);
    }
    else {
        System.out.println(name2);
        System.out.println(name1);
    }
}
}