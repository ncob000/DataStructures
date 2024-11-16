#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        bool is_stack = true, is_queue = true, is_prq = true;
        stack<int> stk;
        queue<int> q;
        priority_queue<int> prq;

        for (int i = 0; i < n; ++i)
        {
            int type, x;
            scanf("%d", &type);

            if (type == 1)
            {
                scanf("%d", &x);
                if (is_stack)
                    stk.push(x);
                if (is_queue)
                    q.push(x);
                if (is_prq)
                    prq.push(x);
            }
            else if (type == 2)
            {
                scanf("%d", &x);
                if (is_stack)
                {
                    if (stk.empty() || stk.top() != x)
                        is_stack = false;
                    else
                        stk.pop();
                }
                if (is_queue)
                {
                    if (q.empty() || q.front() != x)
                        is_queue = false;
                    else
                        q.pop();
                }
                if (is_prq)
                {
                    if (prq.empty() || prq.top() != x)
                        is_prq = false;
                    else
                        prq.pop();
                }
            }
        }

        if (is_stack && !is_queue && !is_prq)
            printf("stack\n");
        else if (!is_stack && is_queue && !is_prq)
            printf("queue\n");
        else if (!is_stack && !is_queue && is_prq)
            printf("priority queue\n");
        else if (!is_stack && !is_queue && !is_prq)
            printf("impossible\n");
        else
            printf("not sure\n");
    }

    return 0;
}
