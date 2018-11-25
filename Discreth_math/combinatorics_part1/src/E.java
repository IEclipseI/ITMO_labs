import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class E {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        //PrintWriter out = new PrintWriter(new File("output.txt"));
        int n = in.nextInt();
        if (n == 0) {
            System.out.print("0\n0 0");
            return;
        }
        int[] inp = new int[n];
        for (int i = 0; i < n; i++) {
            inp[i] = in.nextInt();
        }
        int[][] dp = new int[n + 1][n + 3];
        List<List<List<Integer>>> path = new ArrayList<List<List<Integer>>>();
        for (int i = 0; i < n + 3; i++) {
            path.add(new ArrayList<List<Integer>>());
            for (int j = 0; j < n + 1; j++) {
                path.get(i).add(new ArrayList<Integer>());
            }
        }
        for (int i = 0; i < n + 1; i++) {
            dp[i][0] = Integer.MAX_VALUE / 2;
        }
        for (int i = 0; i < n + 1; i++) {
            for (int j = 2 + i; j < n + 3; j++) {
                dp[i][j] = Integer.MAX_VALUE / 2;
            }
        }
        dp[1][1] = inp[0];
        if (inp[0] > 100) {
            dp[1][2] = inp[0];
            dp[1][1] = Integer.MAX_VALUE / 2;
        } else {
            dp[1][2] = Integer.MAX_VALUE / 2;
        }
        for (int i = 2; i < n + 1; i++) {
            for (int j = 1; j <= 1 + i; j++) {
                if (inp[i - 1] > 100) {
                    dp[i][j] = Math.min(dp[i - 1][j - 1] + inp[i - 1], dp[i - 1][j + 1]);
                    if (dp[i - 1][j - 1] + inp[i - 1] > dp[i - 1][j + 1]) {
                        path.get(j).get(i).addAll(path.get(j + 1).get(i - 1));
                        path.get(j).get(i).add(i);
                    }else {
                        path.get(j).get(i).addAll(path.get(j - 1).get(i - 1));
                    }
                } else {
                    dp[i][j] = Math.min(dp[i - 1][j] + inp[i - 1], dp[i - 1][j + 1]);
                    if (dp[i - 1][j] + inp[i - 1] > dp[i - 1][j + 1]) {
                        path.get(j).get(i).addAll(path.get(j + 1).get(i - 1));
                        path.get(j).get(i).add(i);
                    } else {
                        path.get(j).get(i).addAll(path.get(j).get(i - 1));
                    }
                }
            }
        }
        int min_answer = 0;
        for (int i = n + 1; i > 0; i--) {
            if (dp[n][i] < dp[n][min_answer]) {
                min_answer = i;
            }
        }

        System.out.println(dp[n][min_answer]);
        System.out.print(min_answer - 1 + " ");
        System.out.println(path.get(min_answer).get(n).size());
        for (int k : path.get(min_answer).get(n)
                ) {
            System.out.println(k);
        }

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