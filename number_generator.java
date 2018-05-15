import java.util.*;

class NumberGenerator {
  public static void main(String[] args) {

    int N = Integer.parseInt(args[0]);
    int numOfRequests = Integer.parseInt(args[1]);

    for (int i = 0; i < numOfRequests; i++) {
      Random random = new Random();
      int number = random.nextInt(N) + 1;
      System.out.println(i*10 + " " + number);
    }
  }
}
