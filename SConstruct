# -*- python -*-
# Copyright 2013 the original author or authors.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
# **********************************************************************
# Author:      Owen Wu/wcw/yubing
# Email:       yubing744@163.com
# Created:     2013/07/09
# **********************************************************************
import os

try:
	Import('project')
except:
	project = None
	pass

project = {
	'parent' : project,

	'groupID' : 'dragon',
	'artifactID' : 'dragon-pom',
	'version' : '0.03',
	'packaging' : 'pom',

	'name' : 'dragon',
	'properties' : {
		'project.build.sourceEncoding' : 'UTF-8'
	},

	'modules' : [
		'dragon',
		'game'
	]
}

def build():
	project['cwd'] = os.getcwd()
	project['children'] = []

	parent = project['parent']
	if parent:
		parent['children'].append(project)

	if not project['parent'] and os.path.exists('../SConstruct'):
		SConscript('../SConstruct')
	elif 'modules' in project:
		modules = project['modules']

		for module in Split(modules):
			SConscript(module + '/SConstruct', exports='project')
	else:
		SConscript('./build/Boot.scons', exports='project')
		
build()