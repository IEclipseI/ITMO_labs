import java.io.*;
import java.util.*;
import java.lang.Math;

public class E {
    public static class SetHead {
        int min;
        int max;
        SetItem next;
        SetItem tail;
        int size = 1;
        SetHead() {
        }
    }
    public static class SetItem {
        SetHead head;
        SetItem next;
        SetItem() {
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("dsu.in"));
        PrintWriter out = new PrintWriter(new File("dsu.out"));
        String tmp = br.readLine(); 
        StringBuilder str = new StringBuilder();
        while (tmp != null) {
            str.append(tmp);
            str.append(' ');
            tmp = br.readLine();
        }
        StringTokenizer in = new StringTokenizer(str.toString());
        int n = Integer.parseInt(in.nextToken());
        List<SetItem> items = new ArrayList<SetItem>();

        for (int  i = 0; i < n; i++) {
            SetHead set = new SetHead();
            items.add(set); 
            items.get(i).min = i;
            items.get(i).max = i;
        }
        while (in.hasMoreTokens()) {
            tmp = in.nextToken();
            if (tmp.equals("union")) {
                int k1 = Integer.parseInt(in.nextToken()) - 1;
                int k2 = Integer.parseInt(in.nextToken()) - 1;
                if (items.get(k1).size > items.get(k2).size ) {
                    items.get(k1).head.min = Math.min(items.get(k1).head.min , items.get(k2).head.min); 
                    items.get(k1).head.max = Math.max(items.get(k1).head.max , items.get(k2).head.max);
                    items.get(k1).head.size += items.get(k2).head.size;
                    SetItem item = items.get(k1).head.tail;
                    item.next = items.get(k2).head;
                    while (item.next != null) {
                        item.head = items.get(k1).head;
                        item = item.next; 
                    }
                    item.head = items.get(k1).head;
                    items.get(k1).head.tail = item;

                } else {
                    if (items.get(k1).head != items.get(k2).head) {
                        items.get(k2).head.min = Math.min(items.get(k1).head.min , items.get(k2).head.min); 
                        items.get(k2).head.max = Math.max(items.get(k1).head.max , items.get(k2).head.max);
                        items.get(k2).head.size += items.get(k1).head.size;
                        SetItem item = items.get(k2).head.tail;
                        item.next = items.get(k1).head;
                        while (item.next != null) {
                            item.head = items.get(k2).head;
                            item = item.next; 
                        }
                        item.head = items.get(k2).head;
                        items.get(k2).head.tail = item;
                    }
                }            
            } else {
                int k = Integer.parseInt(in.nextToken()) - 1;
                if (!in.hasMoreTokens()) {
                    out.print(items.get(k).head.min  + 1 +" "+ (items.get(k).head.max + 1)+ " " +items.get(k).head.size);
                    break;
                } else {
                    out.println(items.get(k).head.min  + 1 +" "+ (items.get(k).head.max + 1)+ " " +items.get(k).head.size);
                }    
            }
        }       
        out.close();/**/     
    }
}
