import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class F {
    public static class Soldat {
        int numb;
        Soldat left;
        Soldat right;
        Soldat(){
        }
        Soldat(int n) {
            numb = n;
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("formation.in"));
        PrintWriter out = new PrintWriter(new File("formation.out"));
        int n = Integer.parseInt(in.next());
        int k = Integer.parseInt(in.next());
        Soldat[] form = new Soldat[n];
        for (int i = 0; i < n; i++) {
            form[i] = new Soldat();
            form[i].numb = i + 1;
        }
        for (int i = 0; i < k; i++) {
            String com = in.next();
            if (com.equals("left")) {
                int sold = in.nextInt() - 1;
                int pos = in.nextInt() - 1;
                form[sold].right = form[pos];
                if (form[pos].left != null) {
                    form[pos].left.right = form[sold];
                }
                form[sold].left = form[pos].left;
                form[pos].left = form[sold];
                continue;
            }
            if (com.equals("right")) {
                int sold = in.nextInt() - 1;
                int pos = in.nextInt() - 1;
                form[sold].left = form[pos];
                if (form[pos].right != null) {
                    form[pos].right.left = form[sold];
                }
                form[sold].right = form[pos].right;
                form[pos].right = form[sold];
                continue;
            }
            if (com.equals("leave")) {
                int pos = in.nextInt() - 1; 
                if (form[pos].left != null) {
                    form[pos].left.right = form[pos].right;
                }
                if (form[pos].right != null) {
                    form[pos].right.left = form[pos].left;
                }
                form[pos] = new Soldat(form[pos].numb);
                continue;
            }
            if (com.equals("name")) {
                int pos = in.nextInt() - 1;
                if (form[pos].left == null) {
                    out.print(0 + " ");
                } else {
                    out.print(form[pos].left.numb + " ");
                }
                if (form[pos].right == null) {
                    out.println(0);
                } else {
                    out.println(form[pos].right.numb );
                }
                continue;
            }
        }
                   /**/
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