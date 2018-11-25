import java.io.*;
import java.util.*;
import java.lang.Math;
                              

public class b {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int k = in.nextInt();
        boolean flag = true;
        int[] ans = new int[n];
        Arrays.fill(ans, -2);
        int[] diz = new int[k];
        int[][] ar = new int[k][n];
        int[][] count = new int[k][2];
        for (int i = 0; i < k; i++) {
            boolean mark = false;
            for (int j = 0; j < n; j++) {
                ar[i][j] = in.nextInt();
                if (ar[i][j] != -1) {
                    mark = true;
                }
            }
            if (!mark)  {
                diz[i] = 1;
            }

        }
        while (flag) {
            /*for (int i = 0; i < k; i++) {
                for (int j = 0; j < n; j++) {
                    System.out.print(" " + ar[i][j]);
                }
                System.out.println(" " + diz[i]);
            } */
            flag = false;
            for (int i = 0; i < k; i++) {
                count[i][0] = 0;
                for (int j = 0; j < n; j++) {
                    if (ar[i][j] >= 0) {
                        count[i][0]++;
                        count[i][1] = j;
                    }
                }
            }
            for (int i = 0; i < k; i++) {
                if (count[i][0] == 1) {
                    flag = true;
                    if (diz[i] != 1) {
                        if (ans[count[i][1]] == -2 || ans[count[i][1]] == ar[i][count[i][1]]) {
                            ans[count[i][1]] = ar[i][count[i][1]];
                            diz[i] = 1;
                        } else {
                            System.out.println("YES");
                            return;
                        }
                    }
                    for (int j = 0; j < k; j++) {
                        if (ans[count[i][1]] == ar[j][count[i][1]]) {
                            diz[j] = 1;
                            for (int l = 0; l < n; l++) {
                                ar[j][l] = -1;
                            }
                        } else {
                            ar[j][count[i][1]] = -1;
                        }
                    }
                }
            }
        }
       /* for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(" " + ar[i][j]);
            }
            System.out.println(" " + diz[i]);
        }   */
        
        for (int i = 0; i < k; i++) {
            if (diz[i] == 1) {
                continue;
            }
            boolean test = true; 
            for (int j = 0; j < n; j++) {
                if (ar[i][j] != -1 && ans[j] == -2) {
                    test = false;
                    break;
                }
            }
            if (test) {
                System.out.println("YES");
                return;
            }
        }        
            System.out.println("NO");        
    }
}
                