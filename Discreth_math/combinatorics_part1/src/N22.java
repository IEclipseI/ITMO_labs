import com.sun.javafx.image.IntPixelGetter;

import java.io.*;
import java.util.*;

public class N22 {
    static long countPrefix(int cur, int n) {
        if (n == 0) {
            return 1;
        }
        long[][] dp = new long[n + 1][n + 1];
        dp[n][n] = 1;
        for (int i = 0; i <= n; i++) {
            dp[i][i] = 1;

        }
        for (int i = n - 1; i >= 1 ; i--) {
            for (int j = i + 1; j <= n; j++) {
                dp[j][i] = dp[j - i][i] + dp[j][i + 1];
            }
        }
        if (cur > n) {
            return 0;
        } else {
            return dp[n][cur];
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("part2num.in"));
        PrintWriter out = new PrintWriter(new File("part2num.out"));

        StringTokenizer str = new StringTokenizer(in.next(), "+");
        long numb = 0;
        //System.out.println(countPrefix(4, 4));
        List<Integer> answer = new ArrayList<Integer>();
        int n = 0;
        while(str.hasMoreTokens()) {
            int tmp = Integer.parseInt(str.nextToken());
            n += tmp;
            answer.add(tmp);
        }
        int cur = 1;
        //List<Integer> tmp = new ArrayList<Integer>();
        for (int i = 0; i < answer.size(); i++) {
            //System.out.println(countPrefix(j, n - j));
            for (int j = cur; j <= n; j++) {
                if (j == answer.get(i)) {
                    cur = j;
                    n -= j;
                    break;
                } else {
                    numb += countPrefix(j, n - j);
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