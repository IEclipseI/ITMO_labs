import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class G {
    public static class Head {
        Pacient next;
    }
    public static class Pacient {
        int numb;
        Pacient left;
        Pacient right;
        Pacient(){
        }
        Pacient(int n) {
            numb = n;
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("hospital.in"));
        PrintWriter out = new PrintWriter(new File("hospital.out"));
        int n = Integer.parseInt(in.next());
        int size = 0;
        Pacient first = null;
        Pacient last = null;
        Pacient mid = null;
        for (int i = 0; i < n; i++) {
            String tmp = in.next();
            if (tmp.equals("+")) {
                if (size == 0) {
                    last = new Pacient(in.nextInt());
                    first = last;
                    mid = last;
                    size++;
                } else {
                    last.right = new Pacient(in.nextInt());
                    last.right.left = last;
                    last = last.right;
                    if (size % 2 == 0) {
                        mid = mid.right;
                    }
                    size++;
                }
                continue; 
            }
            if (tmp.equals("*")) {
                if (size == 0) {
                    last = new Pacient(in.nextInt());
                    first = last;
                    mid = last;
                } else {
                    if (size != 1) {
                        mid.right.left = new Pacient(in.nextInt());
                        mid.right.left.right = mid.right;
                        mid.right.left.left = mid;
                        mid.right = mid.right.left;
                    } else {
                        mid.right = new Pacient(in.nextInt());
                        mid.right.left = mid;
                        last = mid.right;
                    }
                    if (size % 2 == 0) {
                        mid = mid.right;
                    }
                }
                size++;
                continue; 
            }
            out.println(first.numb);
            if (size == 1) {
                first = null;
                last = null;
                mid = null;
                size--;
                continue;
            }
            if (size % 2 == 0) {
                mid = mid.right;
            }
            first = first.right;
            first.left = null;
            size--;
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