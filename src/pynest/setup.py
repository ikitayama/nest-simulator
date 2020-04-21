# -*- coding: utf-8 -*-
#
# setup.py
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.

from distutils.core import setup

setup(
    name='PyNEST',
    version='nest-3@7c9ab01',
    description='PyNEST provides Python bindings for NEST',
    author='The NEST Initiative',
    url='https://www.nest-simulator.org',
    license='GPLv2+',
    packages=['nest', 'nest.tests', 'nest.tests.test_sp',
              'nest.tests.test_topology', 'nest.lib'],
    package_dir={'nest': '/p/project/cjzam11/kitayama1/projects/nest-simulator/pynest/nest'},
    package_data={
        'nest': ['pynest-init.sli'],
        'nest.tests': ['test_aeif_data_lsodar.dat'],
    },
)
