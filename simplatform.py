from nmigen.build.dsl import Attrs, Pins, Resource
from nmigen.build import Platform, Clock
from nmigen.build.run import BuildPlan
from nmigen.back.pysim import Simulator

class SimBuildPlan(BuildPlan):
    def __init__(self, *, fragment):
        self.fragment = fragment

    def execute_local(self, root="build", *, run_script=True):
        print('execute_local')
        sim = Simulator(self.fragment, platform=self)
        with sim.write_vcd('top.vcd'):
            sim.run_until(4, run_passive=True)
        print('ok')

class SimPlatform(Platform):
    # Abstract
    connectors = []
    required_tools = []
    resources = [
        Resource('sync', 0, Pins('sync', dir='i'), Clock(10)),
        Resource('led', 0, Pins('led0', dir='o')),
        Resource('led', 1, Pins('led1', dir='o')),
        Resource('led', 2, Pins('led2', dir='o')),
        Resource('led', 3, Pins('led3', dir='o')),
    ]
    def toolchain_prepare(self, fragment, name, **kwargs):
        print('toolchain_prepare {}'.format(name))


        return SimBuildPlan(fragment=fragment)
    
    # Build
    toolchain = ''
    default_clk = 'sync'
    
    def create_missing_domain(self, name):
        print('create_missing_domain')
        return super().create_missing_domain(name)

    #     if name=='sync':
    #         return super().create_missing_domain(name)
    #     else:
    #         print('create_missing_domain: {}', name)
