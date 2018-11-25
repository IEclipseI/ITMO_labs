import java.io.*;
import java.util.*;
import java.lang.Math;


public class f {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] ar = new int[(int)Math.pow(2, n) + 1];
        int[] ans = new int[(int)Math.pow(2, n) + 1];
        String[] str = new String[(int)Math.pow(2, n)]; 
        for (int i = 0; i < (int)Math.pow(2, n); i++) {
            str[i] = in.next();
            ar[i] = in.nextInt();
        }
        ans[0] = ar[0];
        for (int i = 1; i < (int)Math.pow(2, n); i++) {
            for (int j = 0; j < (int)Math.pow(2, n) - i; j++) {
                ar[j] = (ar[j] + ar[j + 1]) % 2;   
            }
            ans[i] = ar[0];
        }
        for (int i = 0; i < (int)Math.pow(2, n); i++) {
            System.out.println(str[i] + " " + ans[i]);
        }
    }
}
