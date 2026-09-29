#include "list.h"
#include <iostream>

using namespace std;

int passed = 0;

string getList(List &l) {
    string s = "";
    int size = l.Count();
    for (int i = 0; i < size; i++) {
        s += to_string(l.GetItem(i));
        if (i < size - 1) s += " ";
    }
    return s;
}

void showList(List &l) { cout << "List: [" << getList(l) << "]\n"; }

void expectEq(string expect, string result) {
    if (result == expect) {
        passed++;
        cout << "Test passed: " << result << '\n';
    } else {
        cout << "Test failed: expected " << expect << ", got " << result
             << '\n';
        throw std::runtime_error("Test failed");
    }
}

void testOperation(auto operation, string expect, List &l) {
    try {
        operation();
    } catch (const std::out_of_range &e) {
        cout << "Caught exception: " << e.what() << '\n';
        throw;
    }

    expectEq(expect, getList(l));
}

void testOutOfRange(auto operation) {
    try {
        operation();
    } catch (const std::out_of_range &e) {
        passed++;
        cout << "Test passed: " << e.what() << '\n';
        return;
    }
    cout << "Test failed: expected exception, got none" << '\n';
    throw std::runtime_error("Test failed");
}

int main() {
    List l;
    cout << "====< List Test Suit >====" << '\n';
    cout << "\nTest Add, GetItem and Count" << '\n';
    testOperation(
        [&]() {
            l.Add(1);
            l.Add(2);
            l.Add(3);
        },
        "1 2 3", l);

    cout << "\nTest Insert" << '\n';
    testOperation(
        [&]() {
            l.Insert(0, 0);
            l.Insert(4, 4);
            l.Insert(2, 5);
        },
        "0 1 5 2 3 4", l);

    cout << "\nTest Remove" << '\n';
    testOperation(
        [&]() {
            l.Remove(5);
            l.Remove(0);
            l.Remove(4);
        },
        "1 2 3", l);

    cout << "\nTest Contains" << '\n';
    {
        string expect = "1 1 0";
        string result;
        result = l.Contains(1) ? "1" : "0";
        result += " ";
        result += l.Contains(2) ? "1" : "0";
        result += " ";
        result += l.Contains(-1) ? "1" : "0";
        expectEq(expect, result);
    }

    cout << "\nTest IndexOf" << '\n';
    {
        string expect = "0 1 -1";
        string result;
        result = to_string(l.IndexOf(1));
        result += " ";
        result += to_string(l.IndexOf(2));
        result += " ";
        result += to_string(l.IndexOf(-1));
        expectEq(expect, result);
    }

    cout << "\nTest LastIndexOf" << '\n';
    l.Add(3);
    {
        string expect = "3 1 -1";
        string result;
        result = to_string(l.LastIndexOf(3));
        result += " ";
        result += to_string(l.LastIndexOf(2));
        result += " ";
        result += to_string(l.LastIndexOf(-1));
        expectEq(expect, result);
    }

    cout << "\nTest RemoveAt" << '\n';
    testOperation(
        [&]() {
            l.RemoveAt(0);
            l.RemoveAt(l.Count() - 1);
        },
        "2 3", l);

    cout << "\nTest Clear" << '\n';
    testOperation([&]() { l.Clear(); }, "", l);

    cout << "\nTest SetItem" << '\n';
    {
        List sl;
        sl.Add(1);
        sl.Add(2);
        sl.Add(3);
        testOperation(
            [&]() {
                sl.SetItem(0, 9);
                sl.SetItem(1, 8);
                sl.SetItem(2, 7);
            },
            "9 8 7", sl);
        testOperation([&]() { sl.SetItem(1, 0); }, "9 0 7", sl);
    }

    cout << "\nTest Remove return value" << '\n';
    {
        List rl;
        rl.Add(1);
        rl.Add(2);
        rl.Add(3);
        rl.Add(2);
        string result;
        result = rl.Remove(2) ? "1" : "0";
        result += " ";
        result += rl.Remove(99) ? "1" : "0";
        result += " ";
        result += rl.Remove(2) ? "1" : "0";
        expectEq("1 0 1", result);
        expectEq("1 3", getList(rl));
    }

    cout << "\nTest Remove only drops first occurrence" << '\n';
    {
        List rl;
        rl.Add(1);
        rl.Add(2);
        rl.Add(3);
        rl.Add(2);
        testOperation([&]() { rl.Remove(2); }, "1 3 2", rl);
    }

    cout << "\nTest first vs last occurrence" << '\n';
    {
        List dl;
        dl.Add(3);
        dl.Add(1);
        dl.Add(3);
        dl.Add(2);
        dl.Add(3);
        expectEq("0 1 3 -1", to_string(dl.IndexOf(3)) + " " +
                                 to_string(dl.IndexOf(1)) + " " +
                                 to_string(dl.IndexOf(2)) + " " +
                                 to_string(dl.IndexOf(-1)));
        expectEq("4 1 3 -1", to_string(dl.LastIndexOf(3)) + " " +
                                 to_string(dl.LastIndexOf(1)) + " " +
                                 to_string(dl.LastIndexOf(2)) + " " +
                                 to_string(dl.LastIndexOf(-1)));
        expectEq("1 1 1 0", string(dl.Contains(3) ? "1" : "0") + " " +
                                string(dl.Contains(1) ? "1" : "0") + " " +
                                string(dl.Contains(2) ? "1" : "0") + " " +
                                string(dl.Contains(99) ? "1" : "0"));
    }

    cout << "\nTest searches on empty list" << '\n';
    {
        List el;
        expectEq("0", el.Contains(1) ? "1" : "0");
        expectEq("-1", to_string(el.IndexOf(1)));
        expectEq("-1", to_string(el.LastIndexOf(1)));
        expectEq("0", to_string(el.Count()));
    }

    cout << "\nTest Remove down to empty" << '\n';
    {
        List sl;
        sl.Add(7);
        testOperation([&]() { sl.Remove(7); }, "", sl);
        expectEq("0", to_string(sl.Count()));
        expectEq("0", sl.Remove(7) ? "1" : "0");
        testOutOfRange([&]() { sl.GetItem(0); });

        List ml;
        ml.Add(1);
        ml.Add(2);
        ml.Add(3);
        testOperation([&]() { ml.Remove(1); }, "2 3", ml);
        testOperation([&]() { ml.Remove(3); }, "2", ml);
        testOperation([&]() { ml.Remove(2); }, "", ml);
        expectEq("0", to_string(ml.Count()));
    }

    cout << "\nTest RemoveAt down to empty" << '\n';
    {
        List sl;
        sl.Add(7);
        testOperation([&]() { sl.RemoveAt(0); }, "", sl);
        expectEq("0", to_string(sl.Count()));
        testOutOfRange([&]() { sl.GetItem(0); });

        List ml;
        ml.Add(1);
        ml.Add(2);
        ml.Add(3);
        testOperation([&]() { ml.RemoveAt(2); }, "1 2", ml);
        testOperation([&]() { ml.RemoveAt(1); }, "1", ml);
        testOperation([&]() { ml.RemoveAt(0); }, "", ml);
        expectEq("0", to_string(ml.Count()));
    }

    cout << "\nTest reuse after Clear" << '\n';
    {
        List cl;
        cl.Add(1);
        cl.Add(2);
        cl.Clear();
        testOperation(
            [&]() {
                cl.Add(5);
                cl.Add(6);
            },
            "5 6", cl);
    }

    cout << "\nTest duplicate values" << '\n';
    {
        List du;
        testOperation(
            [&]() {
                du.Add(4);
                du.Add(4);
                du.Add(4);
            },
            "4 4 4", du);
        expectEq("3", to_string(du.Count()));
        testOperation([&]() { du.RemoveAt(1); }, "4 4", du);
    }

    l.Add(0);
    l.Add(1);
    l.Add(2);
    cout << "\n====< Throwable List Tests Suit >====" << '\n';
    showList(l);

    cout << "\n---< Test Insert >---" << '\n';
    cout << "\nnegative index" << '\n';
    testOutOfRange([&]() { l.Insert(-1, 10); });
    showList(l);
    cout << "\nindex > Count" << '\n';
    testOutOfRange([&]() { l.Insert(l.Count() + 1, 10); });
    showList(l);

    cout << "\n---< Test GetItem >---" << '\n';
    cout << "\nempty list" << '\n';
    testOutOfRange([&]() {
        List l;
        l.GetItem(0);
    });
    showList(l);
    cout << "\nnegative index" << '\n';
    testOutOfRange([&]() { l.GetItem(-1); });
    showList(l);
    cout << "\nindex > Count" << '\n';
    testOutOfRange([&]() { l.GetItem(l.Count()); });
    showList(l);

    cout << "\n---< Test SetItem >---" << '\n';
    cout << "\nempty list" << '\n';
    testOutOfRange([&]() {
        List l;
        l.SetItem(0, 10);
    });
    showList(l);
    cout << "\nnegative index" << '\n';
    testOutOfRange([&]() { l.SetItem(-1, 10); });
    showList(l);
    cout << "\nindex > Count" << '\n';
    testOutOfRange([&]() { l.SetItem(l.Count(), 10); });
    showList(l);

    cout << "\n---< Test RemoveAt >---" << '\n';
    cout << "\nempty list" << '\n';
    testOutOfRange([&]() {
        List l;
        l.RemoveAt(0);
    });
    showList(l);
    cout << "\nnegative index" << '\n';
    testOutOfRange([&]() { l.RemoveAt(-1); });
    showList(l);
    cout << "\nindex > Count" << '\n';
    testOutOfRange([&]() { l.RemoveAt(l.Count()); });
    showList(l);

    cout << "\n====< " << passed << " tests passed >====" << '\n';
}
