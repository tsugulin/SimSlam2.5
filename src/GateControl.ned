simple GateControl
{
    parameters:
        string gatename;
        string action;
        volatile double productionTime @unit(s) = default(0);
    gates:
        input in;
        input from_create @loose;
        output out;
        output res;
}
