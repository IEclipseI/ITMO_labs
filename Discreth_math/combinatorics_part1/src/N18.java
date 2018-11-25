import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class N18 {
    static long countPrefix(String bracket, int n) {
        long[][] dp = new long[n + 1][n + 1];
        int balance = 0;
        for (int i = 0; i < bracket.length(); i++) {
            if (bracket.charAt(i) == '(') {
                balance++;
            } else {
                balance--;
            }
        }
        dp[bracket.length()][balance] = 1;
        for (int i = bracket.length() + 1; i < n + 1; i++) {
            for (int j = 0; j < n; j++) {
                if (j != 0) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
                } else {
                    dp[i][j] = dp[i - 1][j + 1];
                }
            }
        }
        return dp[n][0];
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("brackets2num.in"));
        PrintWriter out = new PrintWriter(new File("brackets2num.out"));
        String str = in.next();

        int n = str.length();
        String answer = "";
        long numb = 0;
        System.out.println(countPrefix("(((", 4));
        char[] ar = {'(', ')'};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                if ((answer + ar[j]).equals(str.substring(0, (answer + ar[j]).length()))) {
                    answer += ar[j];
                    break;
                } else {
                    numb += countPrefix(answer + ar[j], n);
                }
            }
        }
        out.print(numb);
        out.close();
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

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

        long nextInt() {
            return Long.parseLong(next());
        }
    }
}