require 'rubygems'
require 'ffi'

module FacterFFI
  extend FFI::Library
  ffi_lib FFI::Library::LIBC
  ffi_lib "/home/psy/Facter-Android/facter.so"

  class Fact < FFI::Struct
      layout :name, :string,
             :value, :string,
             :code, :int
  end
  attach_function :malloc, [:size_t], :pointer
  attach_function :facter_to_hash, [:pointer], Fact.by_value

  def self.to_hash
    value = 0
    ptr = FFI::Pointer.new(value, 1)
    result = FacterFFI.facter_to_hash(ptr)
  end
end

result = FacterFFI::to_hash
p result
