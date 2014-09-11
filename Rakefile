#------------------------------------------------------------------------------
# Bundler Setup
#------------------------------------------------------------------------------
require "bundler"
begin
  Bundler.setup(:default, :development)
rescue Bundler::BundlerError => e
  raise LoadError.new("Unable to Bundler.setup(): You probably need to run `bundle install`: #{e.message}")
end
require 'rscons'
require 'rbconfig'

#------------------------------------------------------------------------------
# Envrionment Definitions
#------------------------------------------------------------------------------
# Define the compiler environment
Env = Rscons::Environment.new do |env|
  env.build_dir('source','build/obj/source')
  env["CFLAGS"]  += ['--std=c99', '--pedantic', '-Wall', '-Wextra', '-Werror']
  env['CPPPATH'] += Dir['source/**/']
end

# Define the test environment
TestEnv = Env.clone  do |env|
  env.build_dir('source','build/obj/test_source')
  env.build_dir('tests','build/obj/tests/source')
  env['CFLAGS']  += ['-g', '--coverage', '-DLEAK_DETECT_LEVEL=1', '-DTESTING']
  env["LDFLAGS"] += ['--coverage']
  env['CPPPATH'] += Dir['tests/']
end

# Make sure the environment is processed before we quit
at_exit { Env.process; TestEnv.process}

#------------------------------------------------------------------------------
# Main Build Targets
#------------------------------------------------------------------------------
task :default => [:test, :build]

desc "Build the C Data Structures static library"
task :build do
    Env.Library('build/libcds.a', Dir['source/**/*.c'])
    Env.process
end

#------------------------------------------------------------------------------
# Unit Testing Targets
#------------------------------------------------------------------------------
desc "Run all unit tests"
task :test do
    TestEnv.Program('build/test_libcds', Dir['source/**/*.c', 'tests/**/*.c'])
    TestEnv.process
    sh "build/test_libcds"
end

desc "Generate test coverage reports"
task :coverage => [:test] do
    FileList['build/obj/test_source/**/*.gcno'].each do |gcno|
        obj  = gcno.ext('o')
        path = File.dirname(obj)
        gcov = File.basename(obj).ext('c.gcov')
        sh *['gcov', '-a', '-b', '-c', obj] and FileUtils.mv("./#{gcov}","#{path}/#{gcov}")
    end
end

#------------------------------------------------------------------------------
# Cleanup Target
#------------------------------------------------------------------------------
desc "Clean all generated files and directories"
task(:clean) { Rscons.clean }

desc "Clobber all generated files and directories"
task(:clobber) { FileUtils.rm_rf('build') }

