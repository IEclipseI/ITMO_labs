import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class A {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        int n = in.nextInt();
        int k = in.nextInt();
        int[] dp = new int[n + k];
        int[] inp = new int[n];
        for (int i = 0; i < n - 2; i++) {
            dp[k + 1 + i] = in.nextInt();
            inp[1 + i] = dp[k + 1 + i];
        }
        for (int i = 0; i < n; i++) {
            int tmp = Integer.MIN_VALUE;
            for (int j = 1; j <= k; j++) {
                tmp = Math.max(tmp, dp[k + i - j]);
            }
            dp[k + i] += tmp;
        }
        out.println(dp[n + k - 1]);
        int s = n + k;
        List<Integer> answer = new ArrayList<Integer>();
        answer.add(s - k);
        while (true) {
            dp[s - 1] -= inp[s - k - 1];
            for (int i = 1; i <= k; i++) {
                if (dp[s - i - 1] == dp[s - 1]) {
                    s = s - i;
                    answer.add(s - k);
                    break;
                }
            }
            if (s <= k) {
                break;
            }
        }
        int size = answer.size();
        out.println(size - 2);
        for (int i = size - 2; i >= 0 ; i--) {
            out.print(answer.get(i) + " ");
        }
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

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}