public class Registertest {
    public static void main(String[] args) {
    Register register = new Register();

    register.open();

    Customer c1 = new Customer(0, 2);
    Customer c2 = new Customer(3, 1);

    register.addToQueue(c1);
    register.addToQueue(c2);

    register.step();
    System.out.println(register.hasCustomers());
    register.step();
    System.out.println(register.hasCustomers());
    register.step();
    System.out.println(register.hasCustomers());
    }
}
