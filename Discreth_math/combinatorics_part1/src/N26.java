import com.sun.javafx.image.IntPixelGetter;

import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class N26 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("nextsetpartition.in"));
        PrintWriter out = new PrintWriter(new File("nextsetpartition.out"));
        String tmp = in.nextLine();
        StringTokenizer st = new StringTokenizer(tmp);
        int n = Integer.parseInt(st.nextToken());
        int n1 = n;
        int k = Integer.parseInt(st.nextToken());
        while (n != 0) {
            List<Integer> avail = new ArrayList<Integer>();
            List<List<Integer>> inp = new ArrayList<List<Integer>>();
            for (int i = 0; i < k; i++) {
                inp.add(new ArrayList<Integer>());
                st = new StringTokenizer(in.nextLine());
                while (st.hasMoreTokens()) {
                    inp.get(i).add(Integer.parseInt(st.nextToken()));
                }
            }

            for (int i = k - 1; i >= 0; i--) {
                boolean was_changes = false;
                if (avail.size() > 0) {
                    int min = -1;
                    int min_ind = -1;
                    for (int l = 0; l < avail.size(); l++) {
                        if (avail.get(l) > inp.get(i).get(inp.get(i).size() - 1)){
                            if (min > inp.get(i).get(inp.get(i).size() - 1)) {
                                if (avail.get(l) < min) {
                                    min = avail.get(l);
                                    min_ind = l;
                                }
                            } else {
                                min = avail.get(l);
                                min_ind = l;
                            }
                        }
                    }
                    if (min != -1) {
                        inp.get(i).add(min);
                        avail.remove(min_ind);
                        break;
                    }
                }
                for (int j = inp.get(i).size() - 1; j >= 0 ; j--) {
                    if (j != 0) {
                        if (avail.size() > 0) {
                            //if (avail.get(avail.size() - 1) > inp.get(i).get(j)) {
                                int min = avail.get(avail.size() - 1);
                                int min_ind = avail.size() - 1;
                                for (int l = 0; l < avail.size(); l++) {
                                    if (avail.get(l) > inp.get(i).get(j) && avail.get(l) < min){
                                        min = avail.get(l);
                                        min_ind = l;
                                    }
                                }
                                if (min > inp.get(i).get(j)) {
                                    int t = inp.get(i).get(j);
                                    inp.get(i).set(j, min);
                                    was_changes = true;
                                    avail.remove(min_ind);
                                    avail.add(t);
                                    break;
                                }
                            //}
                        }
                    }
                    int t = inp.get(i).get(j);
                    inp.get(i).remove(j);
                    avail.add(t);
                }
                if (was_changes) {
                    break;
                }
            }
            int minus = 0;
            for (int i = 0; i < inp.size(); i++) {
                //System.out.println(inp.get(i).size());
                if (inp.get(i).size() == 0) {
                    minus++;
                }
                //System.out.println(inp.get(i).size());
            }
            out.println(n + " " + (inp.size() + avail.size() - minus));
            System.out.println(inp.size() + " " + avail.size());
            for (int i = 0; i < inp.size(); i++) {
                for (int j = 0; j < inp.get(i).size(); j++) {
                    out.print(inp.get(i).get(j) + " ");
                }
                if (inp.get(i).size() > 0) {
                    out.println();
                }
            }
            Collections.sort(avail);
            for (int i = 0; i < avail.size(); i++) {
                out.println(avail.get(i));
            }
            out.println();
            n = (int)in.nextInt();
            k = (int)in.nextInt();
        }
        //out.println();
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
        String nextLine() throws IOException {
            return br.readLine();
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