import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        BigInteger[] ss = new BigInteger[3];
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        String n;
        for (int i=1;i<=T;i++) {
            n = in.next();
            ss[0] = new BigInteger(n);
            n = in.next();
            ss[1] = new BigInteger(n);
            ss[2] = ss[0].add(ss[1]);
            System.out.println("Case " + i + ":");
            System.out.println(ss[0] + " + " + ss[1] + " = " + ss[2]);
            if(i!=T) {
                System.out.println();
            }
        }
    }
}
