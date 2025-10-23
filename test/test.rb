# test/test.rb
require 'rspec'

RSpec.describe 'database' do
  def run_script(commands)
    output = nil
    IO.popen("../main", "r+") do |pipe|
      commands.each { |cmd| pipe.puts cmd }
      pipe.close_write
      output = pipe.gets(nil)   # read all output
    end
    output.split("\n")
  end

  it 'inserts and retrieves a row' do
    result = run_script([
      "insert 1 user1 person1@example.com",
      "select",
      ".exit"
    ])
    expect(result).to include(
      "db > Executed.",
      "db > (1, user1, person1@example.com)"
    )
  end

  it 'prints error when table is full' do
    script = (1..1401).map { |i| "insert #{i} user#{i} person#{i}@example.com" }
    script << ".exit"
    result = run_script(script)
    expect(result[-2]).to eq("db > Error: Table full.")
  end

  it 'allows inserting max length strings' do
    long_user = "a"*32
    long_email = "a"*255
    result = run_script([
      "insert 1 #{long_user} #{long_email}",
      "select",
      ".exit"
    ])
    expect(result).to include(
      "db > Executed.",
      "db > (1, #{long_user}, #{long_email})"
    )
  end

  it 'errors if strings are too long' do
    long_user = "a"*33
    long_email = "a"*256
    result = run_script([
      "insert 1 #{long_user} #{long_email}",
      "select",
      ".exit"
    ])
    expect(result).to include(
      "db > String is too long.",
      "db > Executed."
    )
  end

  it 'errors if ID is negative' do
    result = run_script([
      "insert -1 cstack foo@bar.com",
      "select",
      ".exit"
    ])
    expect(result).to include(
      "db > ID must be positive.",
      "db > Executed."
    )
  end
end
