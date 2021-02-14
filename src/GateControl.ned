simple GateControl
{
    parameters:
        string gatename;
        string action;
        volatile double intervalTime @unit(s) = default(0);
    gates:
        input in;
        input from_create @loose;
        output out;
        output res;
}
