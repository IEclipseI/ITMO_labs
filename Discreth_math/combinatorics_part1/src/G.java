import jdk.nashorn.internal.runtime.regexp.joni.Regex;

import java.io.*;
import java.lang.reflect.Array;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class G {
    static String gen_answer(String str, int[][] dp, int l, int r) {
        Long.hashCode(12);
        if (r - l == 1) {
            if (str.charAt(l) == '(' && str.charAt(r) == ')' ||
                    str.charAt(l) == '{' && str.charAt(r) == '}' ||
                    str.charAt(l) == '[' && str.charAt(r) == ']') {
                return str.charAt(l) + ""+  str.charAt(r);
            } else {
                return "";
            }
        }
        if (l == r) {
            return "";
        }
        if (dp[l][r] == dp[l + 1][r - 1] && (str.charAt(l) == '(' && str.charAt(r) == ')' ||
                str.charAt(l) == '{' && str.charAt(r) == '}' ||
                str.charAt(l) == '[' && str.charAt(r) == ']')) {
            return str.charAt(l) + gen_answer(str, dp, l + 1, r - 1) + str.charAt(r);
        }
        for (int i = 0; i <= r - l; i++) {
            if (dp[l][r] == dp[l][l + i] + dp[l + i + 1][r]) {
                return gen_answer(str, dp, l, l + i) + gen_answer(str, dp, l + i + 1, r);
            }
        }

//        if (str.charAt(l) == '(' && str.charAt(r) == ')' ||
//                str.charAt(l) == '{' && str.charAt(r) == '}' ||
//                str.charAt(l) == '[' && str.charAt(r) == ']') {
//            return str.charAt(l) + gen_answer(str, )
//        }
        return "";
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        //PrintWriter out = new PrintWriter(new File("output.txt"));
        String str = in.next();
        int[][] dp = new int[str.length()][str.length()];
        for (int i = 0; i < str.length(); i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE / 2);
            dp[i][i] = 1;
        }
        for (int i = 0; i <= str.length() - 2; i++) {
            if (str.charAt(i) == '(' && str.charAt(i + 1) == ')' ||
                    str.charAt(i) == '{' && str.charAt(i + 1) == '}' ||
                    str.charAt(i) == '[' && str.charAt(i + 1) == ']') {
                dp[i][i + 1] = 0;
            } else {
                dp[i][i + 1] = 2;
            }
        }
        for (int i = 0; i < str.length() - 2; i++) {
            if (str.charAt(i) == '(' && str.charAt( i + 2) == ')' ||
                    str.charAt(i) == '{' && str.charAt(2 + i) == '}' ||
                    str.charAt(i) == '[' && str.charAt(2 + i) == ']') {
                dp[i][i + 2] = 1;
            } else {
                dp[i][i + 2] = Math.min(dp[i][i] + dp[i + 1][i + 2], dp[i][i + 1] + dp[i + 2][i + 2]);
            }
        }
        for (int i = 3; i < str.length(); i++) {
            for (int j = 0; j < str.length() - i; j++) {
                if (str.charAt(j) == '(' && str.charAt(j + i) == ')' ||
                        str.charAt(j) == '{' && str.charAt(j + i) == '}' ||
                        str.charAt(j) == '[' && str.charAt(j + i) == ']') {
                    dp[j][j + i] = dp[j + 1][j + i - 1];
                }
                for (int k = 0; k < i; k++) {
                    dp[j][j + i] = Math.min(dp[j][j + i], dp[j][j + k] + dp[j + 1 + k][j + i]);
                }
            }
        }
        //System.out.println(str.length() - dp[0][str.length() - 1]);
        System.out.print(gen_answer(str, dp, 0, str.length() - 1));
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