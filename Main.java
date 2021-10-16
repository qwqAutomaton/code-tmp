import java.util.Scanner;
class Segtree {
    private class Node {
        public int l, r;
        public long lazy, val;
        public Node() {
            this.l = 0;
            this.r = 0;
            this.lazy = 0;
            this.val = 0;
        }
        public Node(int l, int r, long lazy, long val) {
            this.l = l;
            this.r = r;
            this.lazy = lazy;
            this.val = val;
        }
    }
    private Node[] seg;
    private void pushup(int cur) {
        seg[cur].val = seg[cur * 2].val + seg[cur * 2 + 1].val;
    }
    private void pushdown(int cur) {
        if (seg[cur].lazy != 0) {
            seg[cur * 2].lazy += seg[cur].lazy;
            seg[cur * 2 + 1].lazy += seg[cur].lazy;
            seg[cur * 2].val += seg[cur].lazy * (seg[cur * 2].r - seg[cur * 2].l + 1);
            seg[cur * 2 + 1].val += seg[cur].lazy * (seg[cur * 2 + 1].r - seg[cur * 2 + 1].l + 1);
            seg[cur].lazy = 0;
        }
    }
    private void build(int cur, int l, int r, long[] arr) {
        this.seg[cur] = new Node(l, r, 0, 0);
        if (l == r) {
            this.seg[cur].val = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        this.build(cur * 2, l, mid, arr);
        this.build(cur * 2 + 1, mid + 1, r, arr);
        this.pushup(cur);
    }
    private void _add(int cur, int l, int r, long v) {
        if (l <= seg[cur].l && seg[cur].r <= r) {
            seg[cur].lazy += v;
            seg[cur].val += v * (seg[cur].r - seg[cur].l + 1);
            return;
        }
        pushdown(cur);
        int mid = (seg[cur].l + seg[cur].r) / 2;
        if (l <= mid)
            _add(cur * 2, l, r, v);
        if (r > mid)
            _add(cur * 2 + 1, l, r, v);
        pushup(cur);
    }
    private long _query(int cur, int l, int r) {
        if (l <= seg[cur].l && seg[cur].r <= r) {
            return seg[cur].val;
        }
        pushdown(cur);
        int mid = (seg[cur].l + seg[cur].r) / 2;
        long ans = 0;
        if (l <= mid)
            ans += _query(cur * 2, l, r);
        if (r > mid)
            ans += _query(cur * 2 + 1, l, r);
        pushup(cur);
        return ans;
    }
    public Segtree(long[] arr) {
        int len = arr.length - 1;
        this.seg = new Node[len * 4];
        this.build(1, 1, len, arr);
    }
    public void add(int l, int r, long v) {
        _add(1, l, r, v);
    }
    public long query(int l, int r) {
        return _query(1, l, r);
    }
}
public class Main {
    public static long[] a;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, m;
        n = sc.nextInt();
        m = sc.nextInt();
        a = new long[n + 1];
        for (int i = 1; i <= n; i++) {
            a[i] = sc.nextInt();
        }
        Segtree seg = new Segtree(a);
        for (int i = 1; i <= m; i++) {
            int op, x, y, k;
            op = sc.nextInt();
            if (op == 1) {
                x = sc.nextInt();
                y = sc.nextInt();
                k = sc.nextInt();
                seg.add(x, y, k);
            } else {
                x = sc.nextInt();
                y = sc.nextInt();
                System.out.println(seg.query(x, y));
            }
        }
    }
}

