Inference Engine

Cameron Cross 7193432
Calum Ilott 718610x
Group: COS30019_A02_T016

Features:

- Load the Horn Notation into a format that can be used across all the Inference engines.
- Truth Table and Backward Chaining should work perfectly
- Forward Chaining is nearly correct but does not seem to get the same results as given by the assignment sheet.
- No significant performance issues discovered.

Bugs:

- Forward Chaining gives slightly different results to what is expected.
- No memory cleanup preformed, assumed that the program will exit and clean up itself.

Issues:

- One of our  team members (Vinayak Arora) did not do their section. When asked they submitted the Backward Chaining code of another member and tried to claim it as their own. Their code only changed the push_back() and pop_back() functions to push_front() and pop_front(). These functions dont exist for STL vectors, and the code didnt compile.

Test Cases:
-BC
TELL
a=>b;b=>c;c=>d;d=>e;e=>f;f=>g;g=>h;h=>i;i=>j;j=>k;k=>l;l=>m;m=>n;n=>o;o=>p;p=>q;q=>r;r=>s;s=>t;t=>u;u=>v;v=>w;w=>x;x=>y;y=>z;z=>a;t;
ASK
d

This is a circular set of rules that should still be solvable.

TELL
a=>b;b=>c;c=>d;d=>e;e=>f;f=>g;g=>h;h=>i;i=>j;j=>k;k=>l;l=>m;m=>n;n=>o;o=>p;p=>q;q=>r;r=>s;s=>t;t=>u;u=>v;v=>w;w=>x;x=>y;y=>z;z=>a;
ASK
d

Removing the last t rule could potentially result in an infinite loop, so this was tested. The code does pass this test.



Summary Report:

Cameron Cross created the general framework (main, Engine) so that everyone else could build on top of that.
Cameron Cross also implemented the Backward Chaining implementation.
Calum Ilott implemented the truth table and later the Forward Chaining example.
Cameron Cross and Calum Ilott both reviewed each others code and gave extensive feedback.
Vinayak Arora did not assist and tried to plagerise our work.

Overall Contributions:

Cameron Cross - 50%
Calum Ilott   - 50%
Vinayak Arora - 0 %

Resources:

http://www-scf.usc.edu/~csci460/docs/lecture/lec16.pdf
- Accessed 24th May 2014
- Set of lecture slides that has algorithms for FC and BC.

Lecture Slides
- Accessed 16th May 2014
- Used the diagrams of the Backwards Chaining example to get an understanding of how the BC system should work.

