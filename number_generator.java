import java.util.*;

class NumberGenerator {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int N = scanner.nextInt();
    int numOfRequests = scanner.nextInt();

    for (int i = 0; i < numOfRequests; i++) {
      Random random = new Random();
      int number = random.nextInt(N) + 1;
      System.out.println(i + number)
    }
  }
}
