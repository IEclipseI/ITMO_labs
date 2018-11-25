import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class C {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        //PrintWriter out = new PrintWriter(new File("output.txt"));
        int n = in.nextInt();
        long[][] dp = new long[n][10];
        dp[0][1] = 1;
        dp[0][2] = 1;
        dp[0][3] = 1;
        dp[0][4] = 1;
        dp[0][5] = 1;
        dp[0][6] = 1;
        dp[0][7] = 1;
        dp[0][9] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                switch (j) {
                    case 0: {
                        dp[i][j] = (dp[i - 1][6] + dp[i - 1][4])%1000000000;
                        break;
                    }
                    case 1: {
                        dp[i][j] = (dp[i - 1][6] + dp[i - 1][8])%1000000000;
                        break;
                    }
                    case 2: {
                        dp[i][j] = (dp[i - 1][7] + dp[i - 1][9])%1000000000;
                        break;
                    }
                    case 3: {
                        dp[i][j] = (dp[i - 1][4] + dp[i - 1][8])%1000000000;
                        break;
                    }
                    case 4: {
                        dp[i][j] = (dp[i - 1][3] + dp[i - 1][9] + dp[i - 1][0])%1000000000;
                        break;
                    }
                    case 5: {
                        break;
                    }
                    case 6: {
                        dp[i][j] = (dp[i - 1][1] + dp[i - 1][7] + dp[i - 1][0])%1000000000;
                        break;
                    }
                    case 7: {
                        dp[i][j] = (dp[i - 1][2] + dp[i - 1][6])%1000000000;
                        break;
                    }
                    case 8: {
                        dp[i][j] = (dp[i - 1][1] + dp[i - 1][3])%1000000000;
                        break;
                    }
                    case 9: {
                        dp[i][j] = (dp[i - 1][2] + dp[i - 1][4])%1000000000;
                        break;
                    }
                }
            }
        }
        long res = 0;
        for (int i = 0; i < 10; i++) {
            res=(res + dp[n-1][i])%1000000000;
        }
        System.out.println(res);
    }

    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}