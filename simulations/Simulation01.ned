network Simulation01
{
    submodules:
        create1: Create {
            parameters:
                @display("p=50,100;i=block/source");
        }
        assign1: Assign {
            parameters:
                @display("p=150,100;i=block/control");
        }
        create2: Create {
            parameters:
                @display("p=50,200;i=block/source");
        }
        assign2: Assign {
            parameters:
                @display("p=150,200;i=block/control");
        }
        await1: AwaitResource {
            parameters:
                @display("p=250,150;i=block/circle");
        }
        await2: AwaitGate {
            parameters:
                @display("p=350,150;i=block/circle");
        }
        process: Process {
            parameters:
                @display("p=450,150;i=block/process");
        }
        release: Release {
            parameters:
                @display("p=550,150;i=block/square");
        }
        resource: Resource {
            parameters:
                @display("p=250,275;i=block/table");
        }
        gate: GateKeeper {
            parameters:
                @display("p=350,275;i=block/table");
        }
        create3: Create {
            parameters:
                @display("p=50,400;i=block/source");
        }
        open1: GateControl {
            parameters:
                @display("p=150,400;i=block/switch");
        }
        close1: GateControl {
            parameters:
                @display("p=250,439;i=block/switch");
        }
        open2: GateControl {
            parameters:
                @display("p=350,439;i=block/switch");
        }
        close2: GateControl {
            parameters:
                @display("p=450,400;i=block/switch");
        }
	connections:
        create1.out --> assign1.in;
        create2.out --> assign2.in;
        assign1.out --> await1.in1;
        assign2.out --> await1.in2;
        await1.out --> await2.in;
        await2.out --> process.in;
        process.out --> release.in;
        create3.out --> open1.from_create;
        open1.out --> close1.in;
        close1.out --> open2.in;
        open2.out --> close2.in;
        close2.out --> open1.in;
        await1.res --> resource.from_await;
        release.res --> resource.from_release;
        await2.res --> gate.from_await;
        open1.res --> gate.from_open1;
        close1.res --> gate.from_close1;
        open2.res --> gate.from_open2;
        close2.res --> gate.from_close2;
}
