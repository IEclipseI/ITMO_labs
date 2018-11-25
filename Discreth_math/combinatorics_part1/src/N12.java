import java.io.*;
import java.lang.reflect.Array;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class N12 {
    static void gen(List<List<Integer>> answer , int n, int k, int size, PrintWriter out) throws IOException {
        if (size > n) {
//            if (answer.get(k - 1).isEmpty()) {
//                return;
//            }
            for (int i = 0; i < k; i++) {
                for (int it : answer.get(i)
                     ) {
                    out.print(it + " ");
                }
                out.println();
            }
            out.println();
            return;
        }
        for (int i = 0; i < k; i++) {
            if(answer.get(i).isEmpty()) {
                answer.get(i).add(size);
                gen(answer, n, k, size + 1, out);
                answer.get(i).remove(answer.get(i).size() - 1);
                break;
            }
            answer.get(i).add(size);
            gen(answer, n, k, size + 1, out);
            answer.get(i).remove(answer.get(i).size() - 1);
        }
    }

    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("part2sets.in"));
        PrintWriter out = new PrintWriter(new File("part2sets.out"));
        int n = (int)in.nextInt();
        int k = (int)in.nextInt();
        List<List<Integer>> answer = new ArrayList<List<Integer>>();
        for (int i = 0; i < k; i++) {
            answer.add(new ArrayList<Integer>());
        }
        gen(answer, n, k, 1,out);
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