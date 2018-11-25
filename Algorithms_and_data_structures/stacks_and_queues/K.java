import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class K {
    public static class Sword {
        int numb;
        Sword left;
        Sword right;
        Sword(){
        }
        Sword(int n) {
            numb = n;
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("kenobi.in"));
        PrintWriter out = new PrintWriter(new File("kenobi.out"));
        int n = Integer.parseInt(in.next());
        int size = 0;
        Sword first = null;
        Sword last = null;
        Sword mid = null;
        for (int i = 0; i < n; i++) {
            String tmp = in.next();
            /*System.out.println(i);
            Sword f = first;
            for (int j = 0; j < size; j++) { 
                System.out.print(f.numb + " ");
                f = f.right;
            } */
            if (tmp.equals("add")) {
                if (size == 0) {
                    last = new Sword(in.nextInt());
                    first = last;
                    mid = last;
                } else {
                    //System.out.println(1);
                    last.right = new Sword(in.nextInt());
                    //System.out.println(2);
                    last.right.left = last;
                    //System.out.println(3);
                    last = last.right;
                    if (size > 2 && size % 2 != 0) {
                        mid = mid.right;
                    }
                }
                size++;
                continue; 
            }
            if (tmp.equals("take")) {
                if (size == 1) {
                    last = null;
                    first = null;
                    mid = null;
                    size--;
                    continue;
                }
                if (size != 0) {
                    if (size > 2 && size % 2 == 0) {
                        mid = mid.left;
                    }
                    last = last.left;
                    last.right = null;
                    size--;
                }
                continue;
            }
            if (size == 2) {
                first = last;
                last = mid;
                mid = first;
                first.right = last;
                last.left = first;
                first.left = null;
                last.right = null;
                continue;
            } 
            if (size > 1) {
                first.left = last;
                last.right = first;
                Sword tm = last;
                last = mid;
                first = mid.right;
                last.right = null;
                first.left = null;
                if (size % 2 !=0) {
                    mid = tm.left;
                } else {
                    mid = tm;
                }
                continue;
            }                                   
        }
        //System.out.println(first.numb);
        //System.out.println(mid.numb);
        //System.out.println(last.numb);
        out.println(size);
        for (int i =0; i < size; i++) {
            out.print(first.numb + " ");
            first = first.right;
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