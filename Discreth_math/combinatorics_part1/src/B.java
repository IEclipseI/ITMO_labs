import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class B {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        //PrintWriter out = new PrintWriter(new File("output.txt"));
        int n = in.nextInt();
        int[] dp = new int[n];
        int[] last = new int[n];
        int[] inp = new int[n];
        for (int i = 0; i < n; i++) {
            inp[i] = in.nextInt();
        }
        for (int i = 0; i < n; i++) {
            int tmp = 0;
            int prev = -1;
            for (int j = 0; j < i; j++) {
                if (inp[j] < inp[i]) {
                    if (dp[j] > tmp) {
                        prev = j;
                    }
                    tmp = Math.max(dp[j], tmp);
                }
            }
            dp[i] = 1 + tmp;
            last[i] = prev;
        }
        int max = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] > dp[max]) {
                max = i;
            }
        }
        System.out.println(dp[max]);
        List<Integer> answer = new ArrayList<Integer>();
        while (max != - 1) {
            answer.add(inp[max]);
            max = last[max];
        }
        for (int i = answer.size() - 1; i >=0; i--) {
            System.out.print(answer.get(i) + " ");
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